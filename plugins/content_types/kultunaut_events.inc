<?php
/**
 * @file
 * Ctools plugin definition file.
 */

/**
 * General ctools plugin settings.
 */
$plugin = array(
  'title' => t('Kultunaut events'),
  'category' => t('easyDDB'),
  'description' => t('Show events from kultunaut.dk site'),
  'single' => TRUE,
  'content_types' => 'kultunaut_events_content_type',
  'render callback' => 'kultunaut_events_content_type_render',
  'admin title' => 'Kultunaut events',
  'admin info' => 'kultunaut_events_content_type_admin_info',
  'edit form' => 'kultunaut_events_content_type_edit_form',
);

/**
 * Ctools plugin callback for settings form.
 */
function kultunaut_events_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // Animation delay.
  $form['autoscroll_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Delay (miliseconds)'),
    '#default_value' => !empty($conf['autoscroll_delay']) ? $conf['autoscroll_delay'] : 3000,
    '#description' => t('Time in milliseconds an item will be shown before switching to the next one'),
    '#size' => 4,
  );

  // Limit for number of items shown.
  $form['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Item limit'),
    '#default_value' => isset($conf['limit']) ? $conf['limit'] : 5,
    '#description' => t('Limit amount of items displayed.'),
    '#size' => 4,
  );

  // Cache settings.
  ctools_include('plugins');
  $simple_cache_plugin = ctools_plugin_get_info('panels', 'cache');
  ctools_plugin_load_includes($simple_cache_plugin);
  $pane = $form_state['pane'];
  $default_cache_settings = array(
    'lifetime' => variable_get('ding_nodelist_cache_default_time', 1800),
    'granularity' => 'context',
  );
  $settings = !empty($pane->cache['settings']) ? $pane->cache['settings'] : $default_cache_settings;
  $cache_form = panels_simple_cache_settings_form($settings, $form_state['display'], $pane->pid);
  unset($cache_form['granularity']);

  $form['cache_settings'] = $cache_form;

  // Remove some standard controls.
  unset($form['override_title']);
  unset($form['override_title_text']);
  unset($form['override_title_markup']);

  return $form;
}

/**
 * Edit form submit function.
 */
function kultunaut_events_content_type_edit_form_submit($form, &$form_state) {
  // Set config values.
  $form_state['conf']['autoscroll_delay'] = $form_state['values']['autoscroll_delay'];
  $form_state['conf']['limit'] = $form_state['values']['limit'];
  $form_state['conf']['unique_id'] = 'pane-' . (microtime(TRUE) * 10000);

  // Save cache settings.
  $pane_cache = &$form_state['pane']->cache;
  $pane_cache['method'] = 'simple';
  $pane_cache['settings'] = array(
    'lifetime' => $form_state['values']['lifetime'],
    'granularity' => $form_state['values']['granularity'],
  );

  // Invalidate old cache.
  ctools_include('plugins');
  $simple_cache_plugin = ctools_plugin_get_info('panels', 'cache');
  ctools_plugin_load_includes($simple_cache_plugin);
  $cid = panels_simple_cache_get_id($pane_cache['settings'], $form_state['display'], array(), $form_state['contexts'], $form_state['pane']);
  cache_clear_all($cid, 'cache');
}

/**
 * Render ctools content type.
 */
function kultunaut_events_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();

  $columns = NL_COL_FULL;
  // Prepare classes for widget container.
  $classes = array();
  $classes[] = 'ding_nodelist';
  $classes[] = 'ding_nodelist-horizontal_accordion';
  $classes[] = 'ding_nodelist-col-' . $columns;
  $classes[] = $conf['unique_id'];

  // Build title.
  $title = NULL;
  if (!empty($conf['override_title_text'])) {
    $title = check_plain($conf['override_title_text']);
  }

  // Create proper layout for variable-width lists.
  $map = _ding_nodelist_get_column_map();
  $columns_layout = &drupal_static('ding_nodelist_cols', 0);
  if (!$columns_layout) {
    $classes[] = 'ding_nodelist-col-first';
    $columns_layout += $map[$columns];
  }
  else {
    // Maximum of 4 sub-columns is reached.
    $expected_width = $columns_layout + $map[$columns];
    if ($expected_width == 1) {
      $classes[] = 'ding_nodelist-col-last';
      $columns_layout = 0;
    }
    else {
      $columns_layout += $map[$columns];
    }
  }

  $nodes = kultunaut_events_load($conf['limit']);

  // Load default CSS.
  drupal_add_css(drupal_get_path('module', 'ding_nodelist') . '/css/ding_nodelist.css', 'file');

  // Init JS for widgets.
  _ding_nodelist_add_js(NL_WIDGET_HOR_ACCORDION, $conf['autoscroll_delay'], $conf['unique_id']);
  $image_style = _ding_nodelist_init_image_style(NL_WIDGET_HOR_ACCORDION);
  $theme_func = '_ding_nodelist_widget_' . NL_WIDGET_HOR_ACCORDION;
  $block->content = theme($theme_func, array(
    'items' => $nodes,
    'template' => 'kultunaut_events.event.carousel',
    'links' => '',
    'conf' => array(
      'title' => $title,
      'classes' => implode(' ', $classes),
      'image_style' => $image_style,
      'sorting' => '',
    )
  ));

  return $block;
}

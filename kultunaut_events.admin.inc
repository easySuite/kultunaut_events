<?php
/**
 * @file
 * Kultunaut events Admin UI.
 */

/**
 * Setting form builder.
 */
function kultunaut_events_settings_form() {
  $form = array();

  $form['kultunaut_events_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL to events XML'),
    '#default_value' => variable_get(
      'kultunaut_events_url',
      KULTUNAUT_EVENTS_DEFAULT_URL
    ),
    '#description' => t(
      "URL to XML file with events"
    ),
  );

  return system_settings_form($form);
}

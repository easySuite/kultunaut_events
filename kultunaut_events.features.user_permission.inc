<?php
/**
 * @file
 * kultunaut_events_.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function kultunaut_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer kultunaut_events settings'.
  $permissions['administer kultunaut_events settings'] = array(
    'name' => 'administer kultunaut_events settings',
    'roles' => array(
      'administrators' => 'administrators',
      'local administrator' => 'local administrator',
    ),
    'module' => 'kultunaut_events',
  );

  return $permissions;
}

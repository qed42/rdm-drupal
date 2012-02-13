<?php
/**
 * @file
 * feature_migrate_demo.features.inc
 */

/**
 * Implements hook_node_info().
 */
function feature_migrate_demo_node_info() {
  $items = array(
    'posts' => array(
      'name' => t('Posts'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

<?php

/**
 * @file
 * Views definitions for biblio_views_export module.
 */

/**
 * Implements hook_views_data().
 */
function biblio_views_export_views_data() {
  $data['biblio_views_export']['table']['group'] = t('Custom');
  $data['biblio_views_export']['table']['join'] = array(
    // #global is a special flag which let's a table appear all the time.
    '#global' => array(),
  );

  $data['biblio_views_export']['biblio_exportlinks'] = array(
    'title' => t('Biblio export links'),
    'help' => t('Add biblio export links'),
    'area' => array(
      'handler' => 'views_handler_biblio_exportlinks',
    ),
  );

  return $data;
}

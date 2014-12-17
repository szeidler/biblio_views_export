<?php

/**
 * Biblio export handler to add mass export feature for the current view
 *
 * @ingroup views_field_handlers
 */
class views_handler_biblio_exportlinks extends views_handler_area {
  function query() {
    // do nothing
  }

  function option_definition() {
    $options = parent::option_definition();

    // Override the alter text option to always alter the text.
    $options['alter']['contains']['alter_text'] = array('default' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove the checkbox
    unset($form['alter']['alter_text']);
    unset($form['alter']['text']['#dependency']);
    unset($form['alter']['text']['#process']);
  }

  function render($values) {
    $output = '';

    // check if the view has at least one exportable row
    if ($this->view->total_rows > 0) {
      // reload the view without pager
      $view = views_get_view($this->view->name);
      $view->set_display($this->view->current_display);
      $view->set_items_per_page(0);
      $view->execute();

      $nids = array();
      // loop through non-pager results and collect the nids of every row
      foreach ($view->result as $result) {
        // Check if it is a node view
        if (isset($result->nid)) $nids[] = $result->nid;
        // Check if it is a search_index view
        if (isset($result->entity)) $nids[] = $result->entity;
      }

      // Add a biblio export form with hidden nid variables
      $output = drupal_render(drupal_get_form('biblio_views_export_form', $nids));
    }
    return $output;
  }
}
<?php

/**
 * @file
 * Contains views_handler_biblio_exportlinks.
 */

/**
 * Biblio export handler to add a mass export form for the current view.
 *
 * @ingroup views_area_handlers
 */
class views_handler_biblio_exportlinks extends views_handler_area {
  /**
   * {@inheritdoc}
   */
  public function query() {
    // Do nothing.
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    // Override the alter text option to always alter the text.
    $options['alter']['contains']['alter_text'] = array('default' => TRUE);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove the checkbox.
    unset($form['alter']['alter_text']);
    unset($form['alter']['text']['#dependency']);
    unset($form['alter']['text']['#process']);
  }

  /**
   * Rebuild the view without pager and render the area.
   *
   * @param bool $values
   *   The value being rendered.
   *
   * @return string
   *   Themed export form.
   */
  public function render($values) {
    $output = '';

    // Check if the view has at least one exportable row.
    if ($this->view->total_rows > 0) {
      // Reload the view without pager.
      $view = views_get_view($this->view->name);
      $view->set_display($this->view->current_display);
      $view->set_items_per_page(0);
      $view->execute();

      $nids = array();
      // Loop through non-pager results and collect the nids of every row.
      foreach ($view->result as $result) {
        // Check if it is a node view.
        if (isset($result->nid)) {
          $nids[] = $result->nid;
        }
        // Check if it is a search_index view.
        if (isset($result->entity)) {
          $nids[] = $result->entity;
        }
      }

      // Add a biblio export form with hidden nid variables.
      $output = drupal_render(drupal_get_form('biblio_views_export_form', $nids));
    }
    return $output;
  }
}

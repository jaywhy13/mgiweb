<?php

/**
 * @file
 * Adds options to ThemeKey's adminstration back end and alters drupal forms
 * to add theme select boxes.
 *
 * @see themekey_ui.module
 *
 * @author Karl Fritsche | Cocomore AG (Drupal 7 Port)
 *   @see http://drupal.org/user/619702
 *
 * @author Markus Kalkbrenner | Cocomore AG
 *   @see http://drupal.org/user/124705
 *
 * @author profix898
 *   @see http://drupal.org/user/35192
 */

/**
 * form alter for ui settings forms
 *
 * @param  $form
 * @param  $form_state
 * @param  $form_id
 * @return void
 */
function taxonomy_theme_alter_themekey_ui_settings_form(&$form, $form_state, $form_id) {


  $vocabform = variable_get('themekey_ui_vocabform', 0);
  $form['themekey_ui']['themekey_ui_vocabform'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show theme option in create/edit taxonomy vocabulary forms'),
    '#default_value' => $vocabform,
    '#description' => t('Assign themes from create/edit taxonomy vocabulary forms. This will show a \'Theme\' section on create/edit taxonomy vocabulary pages.'),
  );
  if ($vocabform) {
    $form['themekey_ui']['vocabs'] = array(
      '#type' => 'fieldset',
      '#title' => t('Show \'Theme\' option for vocabularies'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['themekey_ui']['vocabs']['table'] = array(
      '#theme' => 'themekey_ui_table',
      '#header' => array(t('Vocabulary'), t('Enabled')),
    );

    foreach (taxonomy_get_vocabularies() as $vocab) {
      $form['themekey_ui']['vocabs']['table'][$vocab->vid]['title'] = array(
        '#markup' => l($vocab->name, 'admin/structure/taxonomy/'.$vocab->machine_name.'/edit'),
      );
      $form['themekey_ui']['vocabs']['table'][$vocab->vid]['themekey_ui_vocabform|' . $vocab->vid] = array(
        '#type' => 'checkbox',
        '#default_value' => variable_get('themekey_ui_vocabform|' . $vocab->vid, 0),
      );
    }
  }

  $termform = variable_get('themekey_ui_termform', 0);
  $form['themekey_ui']['themekey_ui_termform'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show theme option in create/edit taxonomy term forms'),
    '#default_value' => $termform,
    '#description' => t('Assign themes from create/edit taxonomy term forms. This will show a \'Theme\' section on create/edit taxonomy term pages.'),
  );
  if ($termform) {
    $form['themekey_ui']['term_vocabs'] = array(
      '#type' => 'fieldset',
      '#title' => t('Show \'Theme\' option for terms of vocabularies'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['themekey_ui']['term_vocabs']['table'] = array(
      '#theme' => 'themekey_ui_table',
      '#header' => array(t('Vocabulary'), t('Enabled')),
    );

    foreach (taxonomy_get_vocabularies() as $vocab) {
      $form['themekey_ui']['term_vocabs']['table'][$vocab->vid]['title'] = array(
        '#markup' => l($vocab->name, 'admin/structure/taxonomy/' . $vocab->machine_name)
      );
      $form['themekey_ui']['term_vocabs']['table'][$vocab->vid]['themekey_ui_termform|' . $vocab->vid] = array(
        '#type' => 'checkbox',
        '#default_value' => variable_get('themekey_ui_termform|' . $vocab->vid, 0),
      );
    }
  }

  $form['#submit'][] = 'taxonomy_theme_form_alter_submit';
}


/**
 * Function _taxonomy_theme_form_alter().
 * adds themekey ui select form to curretn form
 */
function _taxonomy_theme_form_alter(&$form, $form_state, $form_id) {
  module_load_include('inc', 'themekey_ui', 'themekey_ui_admin');

  $form_theme = array();
  $theme = '';
  switch ($form_id) {
    case 'taxonomy_form_term':
      if (!variable_get('themekey_ui_termform|' . $form['vid']['#value'], 0)) {
        return;
      }
      $theme = taxonomy_theme_get_theme_by_tid($form['tid']['#value']);
      themekey_ui_theme_select_form($form_theme, t('Theme'), t('Theme to be assigned to current term'), $theme, NULL, FALSE);
      array_splice($form, 4, 0, $form_theme);
      break;

    case 'taxonomy_form_vocabulary':
      if (!variable_get('themekey_ui_vocabform|' . $form['vid']['#value'], 0)) {
        return;
      }
      $theme = taxonomy_theme_get_theme_by_vid($form['vid']['#value']);
      themekey_ui_theme_select_form($form_theme, t('Theme'), t('Theme to be assigned to current vocabulary'), $theme, NULL, FALSE);
      array_splice($form, 3, 0, $form_theme);
      break;
  }

  if (!themekey_check_theme_enabled($theme, TRUE)) {
    $form['themekey_ui_themes']['themekey_ui_theme']['#attributes'] = array('class' => 'error');
  }

  $form['#submit'][] = 'taxonomy_theme_form_alter_submit';
}


/**
 * function _taxonomy_theme_alter_submit().
 * add/save themes set in vocabulary/terms
 * add static rules
 */
function _taxonomy_theme_form_alter_submit($form, &$form_state) {
  switch ($form_state['values']['form_id']) {
    case 'themekey_ui_settings_form':
      themekey_update_static_rule('taxonomy_theme:vocabulary_triggers_theme', $form_state['values']['themekey_ui_vocabform']);
      themekey_update_static_rule('taxonomy_theme:term_triggers_theme', $form_state['values']['themekey_ui_termform']);
      break;

   case 'taxonomy_form_term':
      $item = array(
        'tid' => $form_state['values']['tid'],
        'theme' => $form_state['values']['themekey_ui_theme'],
      );
      //TODO DB LOCK TABLE

      if (db_select('taxonomy_theme_tids', 't')->fields('t', array('tid'))->condition('tid', $form_state['values']['tid'])->execute()->fetchField()) {
        drupal_write_record('taxonomy_theme_tids', $item, array('tid'));
      }
      else {
        drupal_write_record('taxonomy_theme_tids', $item);
      }
      //TODO DB UNLOCK TABLE
      break;

    case 'taxonomy_form_vocabulary':
      $item = array(
        'vid' => $form_state['values']['vid'],
        'theme' => $form_state['values']['themekey_ui_theme'],
      );
      //TODO DB LOCK TABLE
      if (db_select('taxonomy_theme_vids', 't')->fields('t', array('vid'))->condition('vid', $form_state['values']['vid'])->execute()->fetchField()) {
        drupal_write_record('taxonomy_theme_vids', $item, array('vid'));
      }
      else {
        drupal_write_record('taxonomy_theme_vids', $item);
      }
      //TODO DB UNLOCK TABLE
      break;
  }
}

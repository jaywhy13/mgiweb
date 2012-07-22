<?php



/**
 * Form callback.
 */
function fridge_admin_app_form() {

  $fridge_app_defaults = fridge_app_defaults();
  $fridge_app = variable_get('fridge_app', array('client_id' => ''));

  $fridge_app_devel_defaults = fridge_app_devel_defaults();
  $fridge_app_devel = variable_get('fridge_app_devel', array('client_id' => NULL));

  $default_data = fridge_graph($fridge_app_defaults['client_id'], FALSE);
  $devel_default_data = fridge_graph($fridge_app_devel_defaults['client_id']);

  $form['fridge_app'] = array(
    '#type' => 'fieldset',
    '#title' => t('Application'),
    '#tree' => TRUE,
    '#description' => t('Live application, for use on production website.'),
  );

  $form['fridge_app']['client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Application ID'),
    '#description' => t('Enter a number.  Leave blank for !app.', array(
                          '%app_id' => $fridge_app_defaults['client_id'],
                          '!app' => l($default_data['name'], $default_data['link']),
                        )),
    '#default_value' => $fridge_app['client_id'],
    //'#required' => TRUE,
  );

  $form['fridge_app_devel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Development Application'),
    '#tree' => TRUE,
    '#description' => t('For use on testing and development websites.'),
  );

  $form['fridge_app_devel']['client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Development App ID'),
    '#description' => t('Leave blank for !app.', array(
                          '%app_id' => $fridge_app_devel_defaults['client_id'],
                          '!app' => l($devel_default_data['name'], $devel_default_data['link']),
                        )),
    '#default_value' => $fridge_app_devel['client_id'],
  );

  $form['fridge_use_devel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the development application on this website.'),
    '#description' => t('Recomended for development and testing.'),
    '#default_value' => variable_get('fridge_use_devel', FALSE),
  );

  //$form['#validate'] = array('fridge_admin_app_form_validate');
  $form['#submit'] = array('fridge_admin_app_form_submit');

    // Javascript settings
  $form['fridge_add_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Javascript SDK'),
    '#description' => t('Initialize <a href=!fb_js_url target=_blank>facebook\'s javascript</a> on every page.  This enables <a href=!fb_sp_url target=_blank>social plugins</a>, for example a <a href=!fb_lb_url target=_blank>like button</a> by simply adding <em>&lt;fb:like&gt;&lt/fb:like&gt;</em> markup.', array(
                          '!fb_js_url' => 'http://developers.facebook.com/docs/reference/javascript/',
                          '!fb_sp_url' => 'http://developers.facebook.com/docs/plugins/',
                          '!fb_lb_url' => 'http://developers.facebook.com/docs/reference/plugins/like/',
                        )),
    '#default_value' => variable_get('fridge_add_js', TRUE),
  );


  return system_settings_form($form);
}

function fridge_admin_app_form_validate($form, &$form_state) {
  //dpm(func_get_args(), __FUNCTION__);

  foreach (array('fridge_app', 'fridge_app_devel') as $key) {
    if ($client_id = $form_state['values'][$key]['client_id']) {
      try {
        // Use fql, not graph, because graph does not return canvas url.
        $data = fridge_fql("SELECT app_id, api_key, canvas_name, display_name FROM application WHERE app_id = $client_id", FALSE);
        $data2 = fridge_graph($data[0]['app_id']); // For link url.

        // TODO: ensure there is a canvas url.
        // Save everything we need about this app.
        form_set_value($form[$key], array(
                         'client_id' => $data[0]['app_id'],
                         'base_url' => 'http://apps.facebook.com/' . $data[0]['canvas_name'],
                         'name' => $data[0]['display_name'],
                       ), $form_state);
        drupal_set_message(t('Found application !name.', array(
                               '!name' => l($data[0]['display_name'], $data2['link']),
                             )));
      }
      catch (Exception $e) {
        dpm($e, __FUNCTION__);
        form_set_error($key, t('Could not validate application id %id.', array('%id' => $client_id)));
      }
    }
  }
}

function fridge_admin_app_form_submit($form, &$form_state) {
  //dpm(func_get_args(), __FUNCTION__);

  foreach (array('fridge_app', 'fridge_app_devel') as $key) {
    if (!$form_state['values'][$key]['client_id']) {
      // Unset this value, so drupal saves no variable.
      unset($form_state['values'][$key]);
      variable_del($key);
    }
  }
  // @TODO - move this message to fridge_post.module
  drupal_set_message(t("Important! Return to <a href=!url>the settings tab</a>, make sure the application is authorized.", array(
                       '!url' => FRIDGE_PATH_ADMIN_CONFIG,
                       )));
}
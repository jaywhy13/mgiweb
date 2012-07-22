<?php


/**
 * Form callback.
 */
function fridge_connect_admin_form() {
  $app = fridge_app();
  $app_data = fridge_graph($app['client_id'] . '?metadata=1');

  $form['fridge_application'] = array(
    '#type' => 'fieldset',
    '#title' => t('Application'),
    '#description' => t('Using <a target=_blank href=!app_url>%name</a>.  See the <a href=!admin_url>application tab</a> to change this.', array(
                          '!admin_url' => url(FRIDGE_PATH_ADMIN_APP),
                          '!app_url' => $app_data['link'],
                          '%name' => $app_data['name'],
                        )),
  );

  /*
  $form['fridge_connect_test'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connect Test'),
    '#description' => t('Facebook Connect requires Facebook\'s javascript to be initialized, and also an <em>application specifically configured to work with this drupal server</em>.'),
  );

  $form['fridge_connect_test']['button'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class=fridge_not_connected>', '#suffix' => '</div>',
    '#markup' => '<p>Test button: <fb:login-button>Click here to test Facebook Connect</fb:login-button></p><ul><li>If you don\'t see a button, javascript is not initialized.</li><li>Click the button.  If you see "an error occurred..." instead of an authorization dialog, then the application is not configured to work with this server. <br/>(Note, it is not necessary to log into facebook or accept the authorization.)</li></ul>',
  );
  */

  $form['fridge_connect_status_test'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connect Status Test'),
    '#description' => t('Facebook Connect requires Facebook\'s javascript to be initialized, and also an <em>application specifically configured to work with this drupal server</em>.'),
  );

  // Markup to be displayed depending on getLoginStatus result.
  // Takes advantage of the fact that getLoginStatus will not call its callback when app cannot support facebook connect.
  $form['fridge_connect_status_test']['status_no_fb'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="fridge_connect_admin_status fridge_connect_admin_status_no_fb">', '#suffix' => '</div>',
    '#markup' => "<strong>Connect javascript not enabled.</strong>  Either you have not enabled javascript, or Facebook's javascript SDK.",
  );
  $form['fridge_connect_status_test']['status_none'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="fridge_connect_admin_status fridge_connect_admin_status_none">', '#suffix' => '</div>',
    '#markup' => "Connect status: <strong>error</strong>.  Your application cannot support Facebook Connect on this server.",
  );
  $form['fridge_connect_status_test']['status_unknown'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="fridge_connect_admin_status fridge_connect_admin_status_unknown">', '#suffix' => '</div>',
    '#markup' => "Connect status: <strong>OK, not connected</strong>.  Either you are not logged into facebook, or have not authorized the appliction.",
  );
  $form['fridge_connect_status_test']['status_connected'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="fridge_connect_admin_status fridge_connect_admin_status_connected">', '#suffix' => '</div>',
    '#markup' => "Connect status: <strong> OK, connected to Facebook</strong>.",
  );


  drupal_add_js(drupal_get_path('module', 'fridge_connect') . '/fridge_connect.admin.js', array(
                  'type' => 'file',
                  'scope' => 'header',
                  'group' => JS_LIBRARY,
                ));

  return system_settings_form($form);

}

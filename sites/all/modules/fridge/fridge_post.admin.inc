<?php


/**
 * Form callback.
 */
function fridge_post_admin_form() {
  $app = fridge_app();
  $app_data = fridge_graph($app['client_id']);

  $form['fridge_application'] = array(
    '#type' => 'fieldset',
    '#title' => t('Application'),
    '#description' => t('Posting via <a target=_blank href=!app_url>%name</a>.  See <a href=!admin_url>the application tab</a> to change this.', array(
                          '!admin_url' => url(FRIDGE_PATH_ADMIN_APP),
                          '!app_url' => $app['base_url'],
                          '%name' => $app_data['name'],
                        )),
  );

  // Authorization settings.
  $form['fridge_authorization'] = array(
    '#type' => 'fieldset',
    '#title' => t('Authorization'),
    '#description' => t('Posting requires a Facebook account which has authorized the application.'),
  );
  if (!isset($_REQUEST['access_token'])) {
    $form['fridge_authorization']['#description'] .= t('<br/>To authorize an account, visit <a href="!url">the %name authorization form</a>.', array(
                                                         '!url' => fridge_user_token_url(),
                                                         '%name' => $app_data['name'],
                                                       ));
  }

  $user_token = fridge_user_token();
  $site_token = fridge_admin_token();

  $token_options = array();

  if (!$user_token) {
  }
  else {
    try {
      $me = fridge_graph('me', $user_token);
      $user_app_data = fridge_graph('app', $user_token);
      if ($user_app_data['id'] != $app['client_id']) {
        // The app has changed since this token was set.
        drupal_set_message(t('Previous authorization by %name uses %old_app_name, not use the current application %app_name.', array(
                               '%name' => $me['name'],
                               '%old_app_name' => $user_app_data['name'],
                               '%app_name' => $app_data['name'],
                             )), 'warning');
      }
      else {
        $token_options[$user_token] = $me['name'];
      }
    }
    catch (Exception $e) {
      drupal_set_message(t("Could not connect to facebook.  <a href=!url>Refresh your authorization</a> to fix this problem.", array(
                             '!url' => fridge_user_token_url(),
                           )), 'error');
    }
  }

  if ($site_token &&
      $site_token != $user_token) {
    try {
      $site = fridge_graph('me', $site_token);
      $site_app_data = fridge_graph('app', $site_token);
      if (!isset($me) || $site['id'] != $me['id']) {
        if ($site_app_data['id'] != $app['client_id']) {
          // The app has changed since this token was set.
          drupal_set_message(t('Previous authorization by %name uses %old_app_name, not use the current application %app_name.', array(
                                 '%name' => $me['name'],
                                 '%old_app_name' => $site_app_data['name'],
                                 '%app_name' => $app_data['name'],
                               )), 'warning');
        }
        else {
          $token_options[$site_token] = $site['name'];
        }
      }
    }
    catch (Exception $e) {
      drupal_set_message(t("Authorization has expired.  Posts to Facebook will fail until <a href=!url>the application is re-authorized</a>.", array(
                             '!url' => fridge_user_token_url(),
                           )), 'error');
    }
  }

  if (count($token_options)) {
    if (count($token_options) > 1) {
      // @TODO: there must be a better way to highlight the choices.
      $token_options[$site_token] .= ' ' . t("(leave the settings unchanged)");
      $token_options[$user_token] .= ' ' . t("(use the new settings)");
    }
    $form['fridge_authorization']['fridge_access_token'] = array(
      '#type' => 'radios',
      '#title' => t('Facebook accounts'),
      '#options' => $token_options,
      '#default_value' => isset($token_options[$site_token]) ? $site_token : $user_token,
      /*'#description' => t('Post to facebook as the selected user.  <br/>For additional options, <a href=!url>visit the authorization form</a>.', array(
                            '!url' => fridge_user_token_url(),
                            )),*/
    );

  }
  else {
    $form['fridge_authorization']['#description'] = ''; // Remove redundant (confusing) text.
    $form['fridge_authorization']['fridge_user_token'] = array(
      '#markup' => t('Please <a href=!url>authorize the application</a> to continue.', array(
                       '!url' => fridge_user_token_url(),
                     )),
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    );
  }


  // Comment settings
  $form['fridge_cross_post_comments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cross-post comments'),
    '#description' => t('Make a local copy of comments posted on facebook.'),
    '#default_value' => variable_get('fridge_cross_post_comments', FALSE),
  );

  return system_settings_form($form);

}

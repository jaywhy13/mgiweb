<?php

drupal_add_css(drupal_get_path('module', 'fb') . '/fridge.theme.css');


function theme_fridge_markup($not_connected_markup, $connected_markup, $options = array()) {
  if ($not_connected_markup == $connected_markup) {
    return $not_connected_markup;
  }

  // Merge in defaults
  $options += array(
    'wrapper' => 'div',
  );

  $output = '';
  if ($not_connected_markup) {
    $output .= '<' . $options['wrapper'] . ' class=fridge_not_connected>' . $not_connected_markup . '</' . $options['wrapper'] . '>';
  }
  if ($connected_markup) {
    $output .= '<' . $options['wrapper'] . ' class=fridge_connected>' . $connected_markup . '</' . $options['wrapper'] . '>';
  }
  return $output;
}

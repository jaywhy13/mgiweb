<?php 
	function mgi_preprocess_page(&$variables, $hook)
	{
		// Get the alias for the page being viewed
		$alias = drupal_get_path_alias($_GET['q']);
		if ($alias != $_GET['q']) {
			$template_filename = 'page';
			 
			   //Break it down for each piece of the alias path
				foreach (explode('/', $alias) as $path_part) {
				$template_filename = $template_filename . '__' . $path_part;
				$variables['theme_hook_suggestions'][] = $template_filename;
				
			}
		}
		$alias = explode('/', $alias);
		$specificCSS = path_to_theme() . '/css/' . $alias[0].'.css';
		if(file_exists($specificCSS))
		{
			drupal_add_css($specificCSS, 'theme', 'all');
		}
		$specificJS = path_to_theme() . '/js/' . $alias[0].'.js';
		if(file_exists($specificJS))
		{
			drupal_add_js($specificJS);
		}
	}
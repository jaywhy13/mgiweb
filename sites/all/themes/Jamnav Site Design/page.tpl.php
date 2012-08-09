
		<div id='widthManager'>
			<div id='sidebar'>
				<div id='logo'>	
					<img src='<?php print $logo ;?>'/>
				</div>
				<div id='menu'>
					<?php print render($page['menu']); ?>
				</div>
			</div>
			
			<div id='divider'>
			</div>
			
			<div id='content'>
				<?php print render($page['content']) ?>
			</div>

			<div id='footer'>
				<?php print render($page['footer']) ?>
			</div>
		</div>

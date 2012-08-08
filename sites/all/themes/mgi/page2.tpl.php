<?php ?>

	
		<div id='banner'>
			<div id='mainMenuBar'>
				<div id='menu'>
					<?php print render($page['mainMenu'])?>
				</div>
			
				<div id='logo'>
					<?php print render($page['logo'])?>
				</div>
			</div>
			<div id='slideshow'>
				<?php print render($page['bannerSlideshow'])?>
			</div>
		</div>
		
		<div id='content-wrapper'>
			<div id='leftSideBar'>
				<?php print render($page['leftSideBar']) ?>
			</div>
			
			<div id='content'>
				<?php print render($page['content'])?>
				<div id='contentFooter'>
				</div>
			</div>
			
			<div id='rightSideBar'>
				<?php print render($page['rightSideBar'])?>
				<div id='rightSideBarFooter'>
				</div>
			</div>
			
			<div id='footer'>
				<?php print render($page['footer'])?>
				<div id='footerMenu'>
					<?php print render($page['footerMenu'])?>
				</div>
				<div id='socialFeeds'>
					<?php print render($page['socialFeeds'])?>
				</div>
			</div>
		</div>
	</body>
	
	
	
</html>
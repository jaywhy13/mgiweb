
	<div id="widthManager">
        <div id="topHalf">
		<div id='slider'>
	    	   <?php print render($page['services'])?>
		</div>
	
	    <div id="transparentBar"></div>
            <div id="menuBar">
                <div id="logo">
					<a href='<?php echo $base_path;?>'>	<img src='<?php print $logo?>'/></a>
                </div>
				<div id="menu">
					<?php print render($page['mainMenu'])?>
			     </div>
            </div>
	    
        </div>
		<div id="bottomHalf" class="gradient"> 
				<?php print render($tabs);?>
				<h2 class="pageTitle" ><?php print $title ?> </h2>
				<?php print render($page['content'])?>
		</div>

          <div id="footerMenu">

				<?php print render($page['footerMenu'])?>
          </div>
        </div>
    </div>


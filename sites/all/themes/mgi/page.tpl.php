
	<div id="widthManager">
        <div id="topHalf">
		<div id='slider'>
	    	   <?php print render($page['bannerSlideshow'])?>
		</div>
	
	    <div id="transparentBar"></div>
            <div id="menuBar">
                <div id="logo">
					<img src='<?php print $logo?>'/>
                </div>
				<div id="menu">
					<?php print render($page['mainMenu'])?>
			     </div>
            </div>
	    
        </div>
        
        <div id="bottomHalf">
          
            
          <div id="sideBarLeft" class="gradient">
                <?php print render($page['leftSideBar']) ?>
          </div>
            
          <div id="main" class="gradient">
               <?php print render($page['content'])?>
          </div>
          <div id="sideBarRight">
                <?php print render($page['rightSideBar'])?>
	  </div>
          </div>
          <div id="footerMenu">
		<?php print render($page['footerMenu'])?>
          </div>
        </div>
    </div>


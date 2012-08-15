
	<div id="widthManager">
        <div id="topHalf">
		<div id='slider'>
	    	   <?php print render($page['services'])?>
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
		<div id="mid" class="gradient"> 
			<div id="leftColumn">
					<?php print render($page['leftColumn'])?>
			</div>
			
			<div id="rightColumn">
					<?php print render($page['rightColumn'])?>
			</div>	
		</div>

          <div id="footerMenu">

				<?php print render($page['footerMenu'])?>
          </div>
        </div>
    </div>


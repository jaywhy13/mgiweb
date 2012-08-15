
	<div id="widthManager">
        <div id="topHalf">
		<div id='slider'>
	    	   <?php print render($page['quote'])?>
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
        <div id="mid" >
			<div id="leftTop">
				<?php print render($page['leftTop'])?>
			</div>
			<div id="rightTop">
				<?php print render($page['rightTop'])?>
			</div>
		</div>
		<div id="bios" > <?php print render($page['bios'])?></div>
		
        <div id="bottomHalf">
          <div id = "about">
			<?php print render($page['about'])?>
		  </div>
		  
		  <div id="associates">
				<?php print render($page['associates'])?>
			</div>
			
		   <div id="fellows">
				<?php print render($page['fellows'])?>
		   </div>
            


          </div>
          <div id="footerMenu">
		<?php print render($page['footerMenu'])?>
          </div>
        </div>
    </div>


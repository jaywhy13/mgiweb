
	<div id="widthManager">
        <div id="topHalf">
	
	
	   
            <div id="menuBar">
                <div id="logo">
					<a href='<?php echo $base_path;?>'>	<img src='<?php print $logo?>'/></a>
                </div>
				<div id="menu">
					<?php print render($page['mainMenu'])?>
			     </div>
            </div>
	   	<div id="quote">
			<?php print render($page['quote'])?>
		</div>
	    
        </div>
		<div id="bottomHalf" class="gradient"> 
		<?php print render($page['content'])?>
		</div>

          <div id="footerMenu">
		<?php print render($page['footerMenu'])?>
          </div>
        </div>
    </div>


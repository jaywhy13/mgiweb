
	<div id="widthManager">
        <div id="topHalf">
		<div id='services'>
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
			<div id="service">
					<?php print render($page['service'])?>
			</div>
			<div id="subDeptMenu">
					<?php print render($page['subDeptMenu'])?>
			</div>
			
			<div id="subDepts">
					<?php print render($page['content'])?>
			</div>	
		</div>

          <div id="footerMenu">
		<?php print render($page['footerMenu'])?>
          </div>
        </div>
    </div>


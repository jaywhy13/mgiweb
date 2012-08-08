<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>MGI</title>
</head>

<body>

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
		<?php print render($page['mainMenu'])?>
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
</body>
</html>

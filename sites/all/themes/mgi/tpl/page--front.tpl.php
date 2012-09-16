<?php include ('header.tpl.php');?>
	
	<div id="slider" >
		<?php print render($page['slider']); ?>
	</div>
	<div id="sideBarLeft" class="gradient">
        <?php print render($page['leftSideBar']) ?>
	</div>
            
    <div id="mid" class="gradient">
        <?php print render($page['content'])?>
    </div>
    <div id="sideBarRight">
         <?php print render($page['rightSideBar'])?>
	</div>
<?php include ('footer.tpl.php');?>
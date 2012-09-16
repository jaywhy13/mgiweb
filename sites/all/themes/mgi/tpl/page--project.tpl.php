<?php include ('header.tpl.php');?>
	
	
	<div id="content"> 
		<?php print render($tabs);?>
		<h2 class="pageTitle" ><?php print $title ?> </h2>
		<?php print render($page['content'])?>
	</div>

<?php include ('footer.tpl.php');?>
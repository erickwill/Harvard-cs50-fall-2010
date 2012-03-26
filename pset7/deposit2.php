<?

    // require common code
    require_once("includes/common.php");

    if ($_POST["money"] == "")
    apologize("Please enter an amount!");    
    
    if (!preg_match("/^\d+$/", $_POST["money"]))
    apologize("Invalid deposit!");

    $money = mysql_real_escape_string($_POST["money"]);

    if (!mysql_query("UPDATE users SET cash = cash + $money WHERE uid = $_SESSION[uid]"))
    apologize("ERROR 1");

    redirect("index.php");
?>


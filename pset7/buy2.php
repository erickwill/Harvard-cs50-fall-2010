<?

    // require common code
    require_once("includes/common.php");

    if ($_POST["symbol"] == "")
    apologize("Form incomplete!");    

    if ($_POST["shares"] == "")
    apologize("Form incomplete!");    
    
    if (!preg_match("/^\d+$/", $_POST["shares"]))
    apologize("Invalid amount of shares!");

    $symbol = mysql_real_escape_string($_POST["symbol"]);
    $shares = mysql_real_escape_string($_POST["shares"]);

    $stock = lookup($_POST["symbol"]);

    $total = $stock->price * $shares;


    $result = mysql_query("SELECT * FROM users WHERE uid = $_SESSION[uid]");
    $user = mysql_fetch_array($result);
    
    if ($user[cash] < $total)
    apologize("You cannot afford this transaction!");

    if (!mysql_query("UPDATE users SET cash = cash - $total WHERE uid = $_SESSION[uid]"))
    apologize("ERROR 1");

    if (!mysql_query("INSERT INTO portfolio (uid, symbol, shares) VALUES($_SESSION[uid], '$symbol', $shares)
    ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)"))
       apologize("ERROR 2");

    mysql_query("INSERT INTO history (uid, trans, symbol, price, shares)
    VALUES($_SESSION[uid], 'bought', '$symbol', '$stock->price', '$shares')");

    redirect("index.php");
?>


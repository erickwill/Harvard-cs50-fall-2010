<?

    // require common code
    require_once("includes/common.php");

    if ($_POST["symbol"] == "")
    apologize("Form incomplete!");    

    $symbol = mysql_real_escape_string($_POST["symbol"]);

    $stock = lookup($_POST["symbol"]);

    $result = mysql_query("SELECT shares FROM portfolio WHERE uid = $_SESSION[uid] and symbol = '$symbol'");
  
    $s = mysql_fetch_array($result);
    if ($s == NULL)
    apologize("Stock not found!");

    $total = $stock->price * $s[shares];

    if (!mysql_query("UPDATE users SET cash = cash + $total WHERE uid = $_SESSION[uid]"))
      apologize("ERROR 1");
    if (!mysql_query("DELETE FROM portfolio WHERE uid = $_SESSION[uid] AND symbol = '$symbol'"))
      apologize("ERROR 2");

    mysql_query("INSERT INTO history (uid, trans, symbol, price, shares)
    VALUES($_SESSION[uid], 'sold', '$symbol', '$stock->price', '$s[shares]')");

    redirect("index.php");
?>


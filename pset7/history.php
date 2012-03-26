<?

    // require common code
    require_once("includes/common.php"); 

?>

<!DOCTYPE html>

<html>

  <head>
    <link href="css/styles.css" rel="stylesheet" type="text/css">
    <title>C$50 Finance: History</title>
  </head>

  <body>

    <div id="top">
      <a href="history.php"><img alt="C$50 Finance" height="110" src="images/logo.gif" width="544"></a>
    </div>
<?
    $id = $_SESSION[uid];
    $sql = "SELECT cash FROM users WHERE uid = $id";

    // execute query
    $result = mysql_query($sql);      
    $s = mysql_fetch_array($result);
?>  
    <div id="middle">
    <p><b>HISTORY:</b></p>
    <table border=1>
      <tr>
        <td><b>CASH</b></td>
        <td><? printf(" $%.2f", $s[cash]) ?></td>
      </tr>
    </table>
    <br/>
    <table border=1>
      <tr>
      <td><b>TIME</b></td><td><b>+/-</b></td><td><b>STOCK</b></td><td><b>PRICE</b></td><td><b>SHARES</b></td>
      </tr>
<?
    $result = mysql_query("SELECT * FROM history WHERE uid = $_SESSION[uid]");

    while ($row = mysql_fetch_array($result))
    {
        print('<tr>');
        print('<td>' . $row["time"] . '</td>');
        print('<td>' . $row["trans"] . '</td>');
        print('<td>' . $row["symbol"] . '</td>');
        print('<td>' . $row["price"] . '</td>');
        print('<td>' . $row["shares"] . '</td>');
        print('</tr>');
    }        
?>
    </table>
  </div>
  <div id="bottom">
    <a href="quote.php">quotes</a> | <a href="buy.php">buy</a> | <a href="sell.php">sell</a> | <a
     href="history.php">history</a> | <a href="logout.php">log out</a>
  </div>

  </body>

</html>

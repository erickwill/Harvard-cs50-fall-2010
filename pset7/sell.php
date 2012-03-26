<?

    // require common code
    require_once("includes/common.php");

?>

<!DOCTYPE html>

<html>

  <head>
    <link href="css/styles.css" rel="stylesheet" type="text/css">
    <title>C$50 Finance: Sell Shares</title>
  </head>

  <body>

    <div id="top">
      <a href="sell.php"><img alt="C$50 Finance" src="images/logo.gif"></a>
    </div>
    <h2 align="center">Sell Shares</h2>
    <div id="middle">
      <form action="sell2.php" method="post">
        <table>
          <tr>
            <td>Stock Symbol:</td>
            <td><input name="symbol" type="text"></td>
        <tr></tr>
        <tr>
          <td colspan="2"><input type="submit" value="Sell"></td>
        </tr>
        </table>
      </form>
    </div>
    <br/><br/>
    <div id="bottom">
      <a href="index.php">home</a> | <a href="quote.php">quotes</a> | <a href="buy.php">buy</a> | <a href="logout.php">logout</a>
    </div>
    <hr/>

<?
    $id = $_SESSION[uid];
    $sql = "SELECT cash FROM users WHERE uid = $id";

    // execute query
    $result = mysql_query($sql);      
    $s = mysql_fetch_array($result);
?>  
    <div id="middle">
    <p><font size="5"><b>PORTFOLIO</font></b></p>
    <table border="1">
      <tr>
        <td><font color="green">CASH</font></td>
        <td><? printf(" $%.2f", $s[cash]) ?></td>
      </tr>
    </table>
    <br/>
    <table border="1">
      <tr>
      <td><b>STOCKS</b></td><td><b>SHARES</b></td>
      </tr>
<?
    $result = mysql_query("SELECT symbol, shares FROM portfolio WHERE uid = $_SESSION[uid]");

    while ($row = mysql_fetch_array($result))
    {
    $s = lookup($row["symbol"]);
        print('<tr>');
        print('<td>' . $s->name . '</td>');
        print('<td>' . $row["shares"] . '</td>');
        print('</tr>');
    }        
?>
    </table>
    </div>
  </body>

</html>

<?

    // require common code
    require_once("includes/common.php");

?>

<!DOCTYPE html>

<html>

  <head>
    <link href="css/styles.css" rel="stylesheet" type="text/css">
    <title>C$50 Finance: Buy Stock</title>
  </head>

  <body>

    <div id="top">
      <a href="buy.php"><img alt="C$50 Finance" src="images/logo.gif"></a>
    </div>

    <div id="middle">
      <form action="buy2.php" method="post">
        <table>
          <tr>
            <td>Stock Symbol:</td>
            <td><input name="symbol" type="text"></td>
          </tr>
      <tr>
        <td>Shares:</td>
            <td><input name="shares" type="text"></td>
      </tr>
      <tr>
            <td colspan="2"><input type="submit" value="Buy Shares"></td>
          </tr>
        </table>
      </form>
    </div>

    <div id="bottom">
      <a href="index.php">home</a> | <a href="quote.php">quotes</a> | <a href="sell.php">sell</a> | <a href="logout.php">logout</a>
    </div>

  </body>

</html>

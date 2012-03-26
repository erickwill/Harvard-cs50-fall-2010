<?

    // require common code
    require_once("includes/common.php");

?>

<!DOCTYPE html>

<html>

  <head>
    <link href="css/styles.css" rel="stylesheet" type="text/css">
    <title>C$50 Finance: Get Quote</title>
  </head>

  <body>

    <div id="top">
      <a href="quote.php"><img alt="C$50 Finance" src="images/logo.gif"></a>
    </div>

    <div id="middle">
      <form action="quote2.php" method="post">
        <table>
          <tr>
            <td>Stock Symbol:</td>
            <td><input name="symbol" type="text"></td>
            <td><input type="submit" value="Get Quote"></td>
          </tr>
        </table>
      </form>
    </div>

    <div id="bottom">
      <a href="index.php">home</a> | <a href="buy.php">buy</a> | <a href="sell.php">sell</a> | <a href="logout.php">logout</a>
    </div>

  </body>

</html>

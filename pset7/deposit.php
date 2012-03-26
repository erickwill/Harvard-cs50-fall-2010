<?

    // require common code
    require_once("includes/common.php");

?>

<!DOCTYPE html>

<html>

  <head>
    <link href="css/styles.css" rel="stylesheet" type="text/css">
    <title>C$50 Finance: Deposit Funds</title>
  </head>

  <body>

    <div id="top">
      <a href="deposit.php"><img alt="C$50 Finance" src="images/logo.gif"></a>
    </div>

    <div id="middle">
      <form action="deposit2.php" method="post">
        <table>
          <tr>
            <td>Deposit Amount:</td>
            <td><input name="money" type="text"></td>
          </tr>
      <tr>
            <td colspan="2"><input type="submit" value="Add Funds"></td>
          </tr>
        </table>
      </form>
    </div>

    <div id="bottom">
      <a href="index.php">home</a> | <a href="quote.php">quotes</a> | <a href="buy.php">buy</a> | <a href="sell.php">sell</a> | <a href="logout.php">logout</a>
    </div>

  </body>

</html>

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
      <img alt="C$50 Finance" src="images/logo.gif">
    </div>

<?
    if ($_POST["symbol"] == "")
    apologize2("Enter a stock symbol!");    
    
    // escape username and password for safety
    $symbol = mysql_real_escape_string($_POST["stock"]);

    $stock = lookup($_POST["symbol"]);

    if ($stock == NULL)
    apologize2("Stock not found!");
?>

    <div style="text-align: center">
      A share of <?= $stock->name ?> currently costs $<?= $stock->price ?>.
      <br/><br/>
<!--
      <form method="LINK" action="quote.php">
        <td>
          <input type="submit" value="Get More Quotes">
        </td>
      </form>
-->
    </div>
    <div id="bottom">
      <a href="index.php">home</a> | <a href="quote.php">quotes</a> | <a href="buy.php">buy</a> | <a href="sell.php">sell</a> | <a href="logout.php">logout</a> 
    </div>
  </body>

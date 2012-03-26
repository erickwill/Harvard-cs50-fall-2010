<?

    // require common code
    require_once("includes/common.php");

?>

<!DOCTYPE html>

<html>

  <head>
    <link href="css/styles.css" rel="stylesheet" type="text/css">
    <title>C$50 Finance: Log In</title>
  </head>

  <body>

    <div id="top">
      <a href="register.php"><img alt="C$50 Finance" src="images/logo.gif"></a>
    </div>

    <div id="middle">
      <form action="register2.php" method="post">
        <table>
          <tr>
            <td>Username:</td>
            <td><input name="username" type="text"></td>
          </tr>
          <tr>
            <td>Password:</td>
            <td><input name="password" type="password"></td>
          </tr>  <tr>
            <td>Confirm Password:</td>
            <td><input name="password2" type="password"></td>
          </tr>
          <tr>
            <td colspan="2"><input type="submit" value="Register"></td>
          </tr>
        </table>
      </form>
    </div>

    <div id="bottom">
      Already have an account? <a href="login.php">login</a>
    </div>

  </body>

</html>

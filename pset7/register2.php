<?

    // require common code
    require_once("includes/common.php"); 

    if ($_POST["username"] == "")
    apologize("Form incomplete");    

    if ($_POST["password"] != $_POST["password2"])
    apologize("Passwords don't match");
    
    // escape username and password for safety
    $username = mysql_real_escape_string($_POST["username"]);
    $password = mysql_real_escape_string($_POST["password"]);
    $password2 = mysql_real_escape_string($_POST["password2"]);

    // prepare SQL
    $sql = " INSERT INTO users (username, password, cash) VALUES('$username', '$password', 10000.00)";

    // execute query
    if (!mysql_query($sql))
    apologize("Registration Error!");

    $_SESSION["uid"] = mysql_insert_id();

    // redirect to portfolio
    redirect("index.php");

?>

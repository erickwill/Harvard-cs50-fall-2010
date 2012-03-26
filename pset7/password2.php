<?

    // escape username and password for safety
    $username = mysql_real_escape_string($_POST["username"]);
    dump($username);
    // prepare SQL
    $sql = "SELECT password FROM users WHERE username='$username'";

    if ($sql == NULL)
    apologize("username not found!");

    // execute query
    $result = mysql_query($sql);


    $to = "";
    $subject = "Password";
    $body = "Your password is:\n\n" .
    $result;
    $headers = "From: admin@cs50finance.com\r\n";
    mail($to, $subject, $body, $headers);

    redirect("login.php");
?>

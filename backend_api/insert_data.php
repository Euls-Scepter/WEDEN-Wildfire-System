<?php
// api/insert_data.php

$host = 'aws-0-ap-southeast-1.pooler.supabase.com';
$port = '6543'; 
$dbname = 'postgres';
$username = ‘Euls-Scepter';
$password = 'secret';

try {
    // Establish PDO Connection to Supabase
    $dsn = "pgsql:host=$host;port=$port;dbname=$dbname";
    $pdo = new PDO($dsn, $username, $password);
    
    // Set error mode to exception for debugging
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    // Process incoming POST request from ESP32
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        


        // Sanitize incoming data
        $temperature = filter_input(INPUT_POST, 'temperature', FILTER_SANITIZE_NUMBER_INT);
        $smoke = filter_input(INPUT_POST, 'smoke', FILTER_SANITIZE_NUMBER_INT);
        $status = htmlspecialchars($_POST['status']);

        // Insert query
        $sql = "INSERT INTO sensor_logs (temperature, smoke_level, system_status) VALUES (:temp, :smoke, :status)";
        $stmt = $pdo->prepare($sql);
        
        // Execute with bound parameters
        $stmt->execute([
            'temp' => $temperature, 
            'smoke' => $smoke, 
            'status' => $status
        ]);

        echo "Success: Data securely logged to Supabase.";
    } else {
        echo "Error: Invalid Request Method.";
    }
} catch(PDOException $e) {
    echo "Supabase Connection Failed: " . $e->getMessage();
}
?>

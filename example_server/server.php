<?php

class Controller
{
    public function get()
    {
        $this->contentType('text/plain');
        echo "Welcome cxxurl world!\n";
        echo "Author: xiaozhuai\n";
        echo "Github: https://github.com/xiaozhuai\n";
        echo "Repos: https://github.com/xiaozhuai/cxxurl\n";
        echo "Star this project if you like!\n";
    }

    public function cookie__login()
    {
        $this->contentType('text/plain');
        session_start();
        foreach ($_POST as $k => $v) {
            $_SESSION[$k] = $v;
        }
        echo "Login Suc!\n";
    }

    public function cookie__profile()
    {
        $this->contentType('text/plain');
        session_start();
        if (empty($_SESSION)) {
            echo "Please Login!\n";
            return;
        }
        echo "Welcome back!\n";
        echo "Your profile:\n";
        print_r($_SESSION);
    }

    public function download()
    {
        $this->contentType('image/png');
        echo file_get_contents(__DIR__ . '/tao.png');
    }

    public function post(){
        $this->contentType('text/plain');
        $contentType = trim(explode(';', $_SERVER['HTTP_CONTENT_TYPE'])[0]);
        echo "Content-Type: $contentType\n";
        switch ($contentType){
            case 'application/x-www-form-urlencoded':
                echo 'Key-Values: '; print_r($_POST);
                break;

            case 'application/json':
            case 'text/json':
                echo 'Json body parsed: '; print_r(json_decode(file_get_contents('php://input')));
                break;

            case 'text/plain':
                echo 'Text body: ' . file_get_contents('php://input');
                break;

            case 'multipart/form-data':
                echo 'Key-Values: '; print_r($_POST);
                echo 'Files: '; print_r($_FILES);
                break;

            default:
                echo 'Raw Body, Length: '.$_SERVER['HTTP_CONTENT_LENGTH'];
                break;
        }
    }

    public function header(){
        $this->contentType('text/plain');
        $headers = [];
        foreach ($_SERVER as $k => $v){
            if(substr($k, 0, 5)=='HTTP_'){
                $headers[$k] = $v;
            }
        }
        echo "Request header: \n";
        print_r($headers);
    }

    private function contentType($type)
    {
        header("Content-Type: $type");
    }
}


function get_action_by_path()
{
    //print_r($_SERVER);
    $action = $_SERVER['PHP_SELF'];
    $action = substr($action, 1);
    $action = str_replace('/', '__', $action);
    return $action;
}

$action = get_action_by_path();
$reflector = new ReflectionClass('Controller');
$controller = new Controller();
if ($reflector->hasMethod($action)) {
    $method = $reflector->getMethod($action);
    if ($method->isPublic() && !$method->isAbstract()) {
        $method->invoke($controller);
    } else {
        http_response_code(403);
        echo "Forbidden or not implemented";
    }
} else {
    http_response_code(404);
    echo "Not found";
}
#!/usr/local/php4/bin/php -q
<?
function getJobCode($job) {
    $code_table = array (
        "������" => "005",
        "ȸ���" => "008",
        "�ڿ���" => "998",
        "��Ÿ"   => "999",
        "�ֺ�"   => "997",
        "�л�"   => "021"
    );
    $code = $code_table[$job];
    return $code;
    }

    $db = mysql_connect("www.tinc.co.kr", "webmaster", "web1234");
    mysql_select_db("tincdb001", $db);

    $sql = "select * from home_user";
    $res = mysql_query($sql, $db);
    $num = mysql_num_rows($res);

    for ($i=0; $i<$num; $i++) {
        $job_code = trim(getJobCode(mysql_result($res, $i, "job")));
        if ($job_code =="") continue;
        $name    = mysql_result($res, $i, "name");
        $id      = mysql_result($res, $i, "id");
        $passwd  = mysql_result($res, $i, "passwd");
        $email   = mysql_result($res, $i, "e_mail");
        $phone   = mysql_result($res, $i, "phone2");
        $address = mysql_result($res, $i, "address");
        $post    = substr($address, 0, 7);
        $address = substr($address, 8);
        $jumin   = mysql_result($res, $i, "jumin");

        print "insert into sys_svc_users (svcid, name, passwd, ssid, post, sub_post, job_code, email, tel, addr) values (";
        print "'$id','$name', '$passwd', '$jumin', '$post', '1', '$job_code', '$email', '$phone', '$address'";
        print ")\n";
        }
    ?>

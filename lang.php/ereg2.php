#!/usr/local/php4/bin/php -q
<?
   $string = "leejch123456";
   if (ereg("[^0-9a-z]", $string))
      echo "�ڱ�� �ٺ�";
   else 
      echo "��â�� �ٺ�";
?>

<?
   $scale      = 5; // 1�������� �ڷ��
   $page_scale = 5; // 1ȭ��� ��������
   $total      = 0; // �� �ڷ� ����
   $last       = 0; // ȭ���ϴ� [1] [2] .. ��������ȣ i.e. last window number
   $data       = array();   // �Էµ���Ÿ
   $param      = "";

   //if (!$start) { $start = 0; }

   $sp_page = floor($start / ($scale * $page_scale)) ;

   $rc  = 50;             // �˻��� ��ü ���ڵ� ��
   $num = $rc;    
   for ($i=0; $i<$num; $i++) $data[$i] = $i * 10;

   $total = $num;
   $last  = floor($total / $scale);  
   
   // what's n ?
   // $n = ($start) ? $total - $start : $total;

   // start ���� scale ���� ��
   for ($i=$start; $i<$start + $scale; $i++) {
       //
       // ��ü �ڷ� ���������� ���
       //
       if ($i < $total) {
          echo "\$n = $n \$i = $i <br>";
          // $tpl->assign();
          // $tpl->parse(); ok ?
      }
   }

   $url = "";
   //  �˻� ����� ������ �� ��¼� ���� ũ�� �����츦 ����Ѵ�.
   if ($total > $scale) {
      if ($start+1 > $scale * $page_scale) {
         $pre_start = $start - ($scale * $page_scale);
         $url  = "$PHP_SELF?start=$pre_start";
         $line = "<a href=$url>����</a>";
         echo $line;
      }

      for ($vj=0; $vj<$page_scale; $vj++) {
          $ln = ($sp_page * $page_scale + $vj) * $scale;
          $vk =  $sp_page * $page_scale + $vj + 1;

          if ($ln < $total) {
             if ($ln != $start) {
                $url  = "$PHP_SELF?start=$ln";
                $line = "[" . "<a href=$url>
                         <font size=2 color=black>$vk</font>
                         </a>" ."]";
                echo $line;
             } else{
                $line ="<font size=2 color=blue><b>$vk</b></font>";
                echo $line;
             }
          }
      }

      if ($total > (($sp_page + 1) * $scale * $page_scale)) { 
         $n_start = ($sp_page+1) * $scale * $page_scale ;
         $url     = "$PHP_SELF?start=$n_start";
         $line    = "<a href=$url>���� </a>";
         echo $line;
      }
  }
?>

<?

function uniqueRandom(&$result, $range, $count) 
{
  if ($range < $count) return -1;

  $index = array();                           // �ߺ��� üũ�ϱ� ���� �ӽ� �迭
  for ($i=0; $i<$range; $i++) $index[$i] = 1;    // �ӽ� �迭 �ʱ�ȭ 

  $i = 0;                                     // ������ �����ѹ� ����
  while ($i < $count) {
    $value = rand(0, $range);
    if ($index[$value] == 1) {               // ������ ���� �ѹ� �߰�
      $index[$value] = 0;
      $i++;
      $result[$i] = $value;
    }
  }
}

$problems = array (
  "leech", "dariopo", "spacedye", "yundang", "minsk", "yom", "ddong", "jo", "boss", "kamin"
);      

$index = array();
uniqueRandom($index, 10, 5);

for ($i=0; $i<10; $i++) {
  $v = $problems[$index[$i]];
  echo "$v <br>";
}
?>
~                                                                                                 

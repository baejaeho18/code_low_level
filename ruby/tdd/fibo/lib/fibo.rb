class Fibo
  def Fibo.fibo(n)
    return 0 if n <= 0
    return 1 if n == 1 or n == 2
    return fibo(n-1) + fibo(n-2) if n >=3
  end                        

  def Fibo.add(a, b)
    4
  end
end

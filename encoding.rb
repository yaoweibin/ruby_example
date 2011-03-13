require'iconv'  

class String  

  def to_gbk  
    Iconv.iconv("GBK//IGNORE","UTF-8//IGNORE",self).to_s  
  end  

  def to_utf8  
    Iconv.iconv("UTF-8//IGNORE","GB2312//IGNORE",self).to_s  
  end  

end  

s = "\xC4\xE3\xBA\xC3"

puts s.to_utf8


require'iconv'  


class String  

  def to_gbk  
    Iconv.iconv("GBK//IGNORE//TRANSLIT", "UTF-8//IGNORE//TRANSLIT", self).to_s  
  end  

  def to_utf8  
    Iconv.iconv("UTF-8//IGNORE//TRANSLIT", "GBK//IGNORE//TRANSLIT", self).to_s  
  end  

end  


s = "a\xC4\xE3b\xBA\xC3c"

#puts s
puts s.to_utf8

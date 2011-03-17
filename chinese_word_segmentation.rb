# -*- coding: utf-8 -*-

require 'rubygems'
require 'rmmseg'

text = "知名程序员 Ken Thompson 说：想发现有天赋的程序员，重点在激情，在谈话的过程中你会感受到这种激情有多少。我会问他做过最有趣的程序是什么，然后让他描述该程序的细节。如果经不起我的盘问，或者是发现算法和解决方案有问题，而他不能解释清楚，或不能比我做得更投入，那么他也不是好的程序员。"

RMMSeg::Dictionary.load_dictionaries

algor = RMMSeg::Algorithm.new(text)
loop do
	tok = algor.next_token
	break if tok.nil?
	puts "#{tok.text} [#{tok.start}..#{tok.end}]"
end

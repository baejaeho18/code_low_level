#!/usr/bin/env ruby

framework 'Foundation'

class GameLoop
  def start
    @timer = NSTimer.scheduledTimerWithTimeInterval 0.06,
                                           target: self,
                                           selector: 'refresh_screen:',
                                           userInfo: nil,
                                           repeats: true
  end

  def refresh_screen(timer)
    puts "refresh"
  end

  def stop_refreshing
    @timer.invalidate && @timer = nil if @timer
  end

end

GameLoop.new.start
NSRunLoop.currentRunLoop.runUntilDate(NSDate.distantFuture)
-- testing the class

require 'Ghost'


-- test function

function hello()
	print("Hello!")	
end

-- create new object

g = Ghost.new("HippiGspaengst", 5)
g:info()
g:resume()
g:info()
g:resume()

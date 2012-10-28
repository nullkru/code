-- testing the class

require 'Ghost'


-- test function

function hello()
	print("Hello!")	
end

-- create new object

g = Ghost.new("HippiGspaengst",1351418657,1351425882 )
g:info()
g:resume()
g:info()
g:resume()

-- This is a Lua variable
some_variable = 9 * 6

-- Lua table with values for initialization of Game
config = {
    title = "My table",
    fullScreen = true,
    resolution = {
        width = 800,
        height = 600
    }
}

function factorial(n)
    if n == 0 then
        return 1
    else
        return n * factorial(n - 1)
    end
end

-- Example usage
local number = 5
local result = factorial(number)
print("The factorial of " .. number .. " is " .. result)
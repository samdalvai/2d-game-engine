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

function factorial_recursive(n)
    if n == 0 then
        return 1
    else
        return n * factorial_recursive(n - 1)
    end
end

-- Example usage
local number = 5
local result = factorial_recursive(number)
print("The factorial of " .. number .. " is " .. result)

function factorial_loop(n)
    result = 1
    current = n
    while current >= 0 do
        result = result * current
        current = current -1
    end

    return result
end

-- Example usage
local number = 5
local result = factorial_recursive(number)
print("The factorial of " .. number .. " is " .. result)
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

function factorial_tail_recursive(n)
    if n == 0 then
        return 1
    else
        return n * factorial_tail_recursive(n - 1)
    end
end

-- Example usage
local number = 5
local result = factorial_tail_recursive(number)
print("factorial_tail_recursive of " .. number .. " is " .. result)

function factorial_recursive(n)
    return factorial_recursive_internal(n, 1)
end

function factorial_recursive_internal(n, res)
    if n == 0 then
        return res
    end

    return factorial_recursive_internal(n - 1, res * n)
end

-- Example usage
local number = 5
local result = factorial_recursive(number)
print("factorial_recursive of " .. number .. " is " .. result)

function factorial_loop(n)
    factorial = 1
    current = n
    while current > 0 do
        factorial = result * current
        current = current -1
    end

    return factorial
end

-- Example usage
local number = 5
local result = factorial_loop(number)
print("factorial_loop of " .. number .. " is " .. result)


print("Native cube of 6 = "..cube(6))
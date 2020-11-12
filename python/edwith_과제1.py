def vector_size_check(*vector_variables):
    result = all(len(vector_variables[0]) == len(x) \
        for x in vector_variables[1:])
    return result

def vector_addition(*vector_variables):
    if vector_size_check(*vector_variables) == False:
        raise ArithmeticError
    result = [ sum(t) for t in zip(*vector_variables)]
    return None


def vector_subtraction(*vector_variables):
    if vector_size_check(*vector_variables) == False:
        raise ArithmeticError
    result = [ t[0] - sum(t[1:]) for t in zip(*vector_variables)]
    return result


def scalar_vector_product(alpha, vector_variable):
    result = [alpha * x for x in vector_variable]
    return result
	

def matrix_size_check(*matrix_variables):
    result = all(len(matrix_variables[0]) == len(x) \
        for x in matrix_variables[1:]) and \
        all(vector_size_check(*t) for t in zip(*matrix_variables) )
    return result


def is_matrix_equal(*matrix_variables):
    result = all(all(vector_variables[0] == x \
        for x in vector_variables[1:]) \
        for vector_variables in zip(*matrix_variables))
    return result


def matrix_addition(*matrix_variables):
    if matrix_size_check(*matrix_variables) == False:
        raise ArithmeticError
    result = [[sum(t) for t in zip(*rows)] for rows in zip(*matrix_variables)]
    return result


def matrix_subtraction(*matrix_variables):
    if matrix_size_check(*matrix_variables) == False:
        raise ArithmeticError
    result = [[ t[0] - sum(t[1:]) for t in zip(*rows)] \
        for rows in zip(*matrix_variables)]
    return result


def matrix_transpose(matrix_variable):
    result = [[x for x in vec] for vec in zip(*matrix_variable) ]
    return result


def scalar_matrix_product(alpha, matrix_variable):
    result = [[alpha*x for x in vec] for vec in matrix_variable]
    return result


def is_product_availability_matrix(matrix_a, matrix_b):
    result = vector_size_check(*matrix_a) and vector_size_check(*matrix_b) and \
        len(matrix_a[0]) == len(matrix_b)
    return result


def matrix_product(matrix_a, matrix_b):
    if is_product_availability_matrix(matrix_a, matrix_b) == False:
        raise ArithmeticError
    result = [[sum(a*b for a,b in zip(col, row)) for col in zip(*matrix_b)] \
        for row in matrix_a]
    return result

const table = [
    [ '76', 'a' ], [ '66', 'b' ],
    [ '56', 'c' ], [ '46', 'd' ],
    [ '36', 'e' ], [ '26', 'f' ],
    [ '75', 'g' ], [ '65', 'h' ],
    [ '55', 'i' ], [ '45', 'j' ],
    [ '35', 'k' ], [ '25', 'l' ],
    [ '74', 'm' ], [ '64', 'n' ],
    [ '54', 'o' ], [ '73', 'p' ],
    [ '63', 'q' ], [ '53', 'r' ],
    [ '43', 's' ], [ '33', 't' ],
    [ '72', 'u' ], [ '62', 'v' ],
    [ '52', 'w' ], [ '42', 'x' ],
    [ '32', 'y' ], [ '71', 'z' ]
]
let str = ''

function go(i) {
    if (! (i in table)) return
    let [k, v] = table[i]
    if (str)
        str += `\nElse `
    str += `If T=${k}`
    str += `\nThen "${v}"->Str 1`
    go(i + 1)
    str += `\nIfEnd`
}

go(0)
console.log(str)

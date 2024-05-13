const fs = require('fs')
const path = require('path')

const DL = 'E:/'

fs.readdir('./', function (err, files) {
    for (let k in files) {
        let file = files[k]
        let dir = path.join('./', file)
        fs.stat(dir, function (err, stats) {
            if (stats.isFile() && path.extname(file).toLowerCase() == '.txt') {
                let lines = fs.readFileSync(dir, 'utf8').split('\n')
                let res = ''
                for (let i in lines) {
                    let line = lines[i].replace(/^\s+/g, '').replace(/\s+$/g, '')
                    if (line && line[0] != "'")
                        res += line + '\n'
                }
                fs.writeFileSync(path.join('./dist/', file), res)
                fs.writeFileSync(path.join(DL + '@MainMem/PROGRAM/', file), res)
                console.log(`* ${file} compiled`)
            }
        })
    }
})
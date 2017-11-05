tasks["task_ICC"] = {
  node('hpc-test-node2') {
    stage ("SCM checkout"){    
      checkout scm
      dir('') {
        git url: 'https://github.com/MrBr-github/groovy-test.git'
      }
    }
  }
}

tasks["task_ICC"] = {
  node('hpc-test-node2') {
    stage ("SCM checkout"){    
      sh 'echo "==================== SCM start ===================="'
      checkout scm
      sh 'echo "==================== SCM end ===================="'
      dir('') {
        git url: 'https://github.com/MrBr-github/groovy-test.git'
      sh 'echo "==================== Pipeline END ===================="'
      }
    }
  }
}

#!/usr/bin/env groovy
def pl_tasks = [:]

pl_tasks["task_ICC"] = {
  node('hpc-test-node2') {
    stage ("SCM checkout") {    
      sh 'echo "==================== SCM start ===================="'
      checkout scm
      sh 'echo "==================== SCM end ===================="'
    }
    stage ("Secondary_SCM") {
      sh 'echo "==================== Secondary_SCM ===================="'
      dir('swx_ci') {
        git url: 'https://github.com/MrBr-github/groovy-test.git'
      }
      sh 'echo "==================== Secondary_SCM END ===================="'
    }
    stage ("Run external script") {
      sh 'echo "==================== Run external script ===================="'
      sh 'echo "==================== Run external script  END ===================="'
    }
    stage ("End") {
      sh 'echo "==================== Pipeline END ===================="'
    }
  }
}

parallel pl_tasks

#!/usr/bin/env groovy
node('master') {
  dir('swx_ci') {
    shallowClone()
    git url: 'https://github.com/MrBr-github/swx_ci.git'
  }
  evaluate(readFile("${env.WORKSPACE}/swx_ci/_test_pipeline/tests.groovy"))
}
